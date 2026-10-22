---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 09:35:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 11.52/sec |
| Health Score | 720% |
| Threads | 11 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 58-61 cores)</summary>

```
1792675858 58
1792675863 58
1792675868 58
1792675873 58
1792675878 58
1792675883 58
1792675888 58
1792675893 58
1792675898 58
1792675903 58
1792675908 58
1792675913 58
1792675918 58
1792675923 58
1792675928 58
1792675933 58
1792675938 61
1792675943 61
1792675948 61
1792675953 61
```
</details>

---

