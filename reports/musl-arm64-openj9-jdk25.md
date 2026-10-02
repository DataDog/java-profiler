---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-02 00:58:00 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 40 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 13 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1790916819 32
1790916824 32
1790916829 32
1790916834 32
1790916839 32
1790916844 32
1790916849 32
1790916854 32
1790916859 32
1790916864 32
1790916869 32
1790916874 32
1790916879 32
1790916884 32
1790916889 32
1790916894 32
1790916899 32
1790916904 32
1790916910 32
1790916915 32
```
</details>

---

