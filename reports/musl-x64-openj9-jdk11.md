---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-03 08:18:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 775 |
| Sample Rate | 12.92/sec |
| Health Score | 807% |
| Threads | 9 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (2 unique values: 74-96 cores)</summary>

```
1770119049 96
1770119054 96
1770119059 96
1770119064 96
1770119069 96
1770119074 96
1770119079 96
1770119084 96
1770119089 96
1770119094 96
1770119099 96
1770119104 96
1770119109 96
1770119114 96
1770119119 74
1770119124 74
1770119129 74
1770119134 74
1770119139 74
1770119144 74
```
</details>

---

