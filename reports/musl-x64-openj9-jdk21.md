---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-27 13:40:10 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 25 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 538 |
| Sample Rate | 17.93/sec |
| Health Score | 1121% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 22.83/sec |
| Health Score | 1427% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 25-32 cores)</summary>

```
1769538867 32
1769538872 32
1769538877 32
1769538882 32
1769538887 32
1769538892 32
1769538897 32
1769538902 32
1769538907 32
1769538912 32
1769538917 32
1769538922 32
1769538927 25
1769538932 25
1769538937 25
1769538942 25
1769538947 25
1769538952 25
1769538957 25
1769538962 25
```
</details>

---

