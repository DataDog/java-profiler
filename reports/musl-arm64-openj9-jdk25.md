---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-15 17:55:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 11 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1792100876 34
1792100881 34
1792100886 34
1792100891 29
1792100896 29
1792100901 29
1792100906 29
1792100911 29
1792100916 29
1792100921 29
1792100926 29
1792100931 29
1792100936 29
1792100941 29
1792100946 29
1792100951 34
1792100957 34
1792100962 34
1792100967 34
1792100972 34
```
</details>

---

