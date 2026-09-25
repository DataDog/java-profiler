---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-25 00:58:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (7 unique values: 74-92 cores)</summary>

```
1790312044 76
1790312049 76
1790312054 76
1790312059 76
1790312064 76
1790312069 76
1790312074 76
1790312079 76
1790312084 76
1790312089 76
1790312094 74
1790312099 74
1790312104 82
1790312109 82
1790312114 82
1790312119 82
1790312124 78
1790312129 78
1790312134 86
1790312139 86
```
</details>

---

