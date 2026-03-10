---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-10 13:55:47 EDT

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
| CPU Cores (start) | 66 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 11 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 903 |
| Sample Rate | 15.05/sec |
| Health Score | 941% |
| Threads | 12 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (3 unique values: 64-96 cores)</summary>

```
1773165002 66
1773165008 66
1773165013 66
1773165018 66
1773165023 66
1773165028 66
1773165033 66
1773165038 64
1773165043 64
1773165048 64
1773165053 64
1773165058 64
1773165063 96
1773165068 96
1773165073 96
1773165078 96
1773165083 96
1773165088 96
1773165093 96
1773165098 96
```
</details>

---

