---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-05 09:37:18 EST

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
| CPU Cores (start) | 94 |
| CPU Cores (end) | 96 |
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
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 884 |
| Sample Rate | 14.73/sec |
| Health Score | 921% |
| Threads | 11 |
| Allocations | 423 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1793889078 94
1793889083 94
1793889088 94
1793889093 94
1793889098 94
1793889103 94
1793889108 94
1793889113 94
1793889118 94
1793889123 94
1793889128 94
1793889133 94
1793889138 96
1793889143 96
1793889148 96
1793889153 96
1793889158 96
1793889163 96
1793889168 96
1793889174 96
```
</details>

---

