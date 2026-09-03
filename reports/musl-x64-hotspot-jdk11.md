---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-03 15:56:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 594 |
| Sample Rate | 9.90/sec |
| Health Score | 619% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 846 |
| Sample Rate | 14.10/sec |
| Health Score | 881% |
| Threads | 9 |
| Allocations | 556 |

<details>
<summary>CPU Timeline (5 unique values: 51-76 cores)</summary>

```
1788465036 76
1788465041 76
1788465046 76
1788465051 76
1788465056 76
1788465061 74
1788465066 74
1788465071 74
1788465076 74
1788465081 74
1788465086 54
1788465091 54
1788465096 54
1788465101 54
1788465106 56
1788465111 56
1788465116 56
1788465121 56
1788465126 56
1788465131 56
```
</details>

---

