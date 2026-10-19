---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-18 21:23:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 8 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1792372789 64
1792372794 64
1792372799 64
1792372804 64
1792372809 64
1792372814 64
1792372819 64
1792372824 64
1792372829 64
1792372834 64
1792372839 64
1792372844 64
1792372849 64
1792372854 64
1792372859 64
1792372864 64
1792372869 64
1792372874 64
1792372879 64
1792372884 64
```
</details>

---

