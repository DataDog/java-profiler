---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 10:41:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 14 |
| Allocations | 116 |

<details>
<summary>CPU Timeline (1 unique values: 51-51 cores)</summary>

```
1793633863 51
1793633868 51
1793633873 51
1793633878 51
1793633883 51
1793633888 51
1793633893 51
1793633898 51
1793633903 51
1793633908 51
1793633913 51
1793633918 51
1793633923 51
1793633928 51
1793633933 51
1793633938 51
1793633943 51
1793633948 51
1793633953 51
1793633958 51
```
</details>

---

