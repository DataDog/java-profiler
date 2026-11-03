---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-03 05:55:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 877 |
| Sample Rate | 14.62/sec |
| Health Score | 914% |
| Threads | 10 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (3 unique values: 77-81 cores)</summary>

```
1793703011 81
1793703016 81
1793703021 81
1793703026 79
1793703031 79
1793703036 79
1793703041 79
1793703046 79
1793703051 79
1793703056 79
1793703061 79
1793703066 77
1793703071 77
1793703076 77
1793703081 77
1793703086 77
1793703091 77
1793703096 77
1793703101 77
1793703106 77
```
</details>

---

