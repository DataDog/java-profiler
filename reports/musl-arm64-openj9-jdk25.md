---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 06:57:00 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 14 |
| Allocations | 140 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795434740 64
1795434745 64
1795434750 64
1795434755 64
1795434760 64
1795434765 64
1795434770 64
1795434775 64
1795434780 64
1795434785 64
1795434790 64
1795434795 64
1795434800 64
1795434805 64
1795434810 64
1795434815 64
1795434820 64
1795434825 64
1795434830 64
1795434835 64
```
</details>

---

