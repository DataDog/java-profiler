---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-06 05:37:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 67 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 474 |
| Sample Rate | 7.90/sec |
| Health Score | 494% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 649 |
| Sample Rate | 10.82/sec |
| Health Score | 676% |
| Threads | 11 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (4 unique values: 61-71 cores)</summary>

```
1791279097 67
1791279102 67
1791279107 67
1791279112 67
1791279117 67
1791279122 67
1791279127 67
1791279132 69
1791279137 69
1791279142 67
1791279147 67
1791279152 69
1791279157 69
1791279162 69
1791279167 69
1791279172 69
1791279177 69
1791279182 69
1791279187 69
1791279192 71
```
</details>

---

