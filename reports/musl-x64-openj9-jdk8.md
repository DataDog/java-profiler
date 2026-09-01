---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-01 14:09:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 68-88 cores)</summary>

```
1788285797 88
1788285802 88
1788285807 68
1788285812 68
1788285817 68
1788285822 68
1788285827 68
1788285832 68
1788285837 68
1788285842 68
1788285847 76
1788285852 76
1788285857 76
1788285862 76
1788285867 76
1788285872 76
1788285877 76
1788285882 76
1788285887 76
1788285892 76
```
</details>

---

