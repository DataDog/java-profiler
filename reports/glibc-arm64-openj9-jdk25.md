---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-27 13:25:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 228 |
| Sample Rate | 3.80/sec |
| Health Score | 237% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 22-32 cores)</summary>

```
1795803652 32
1795803657 32
1795803662 32
1795803667 32
1795803672 32
1795803677 32
1795803682 32
1795803687 32
1795803692 32
1795803697 32
1795803702 32
1795803707 32
1795803712 27
1795803717 27
1795803722 27
1795803727 22
1795803732 22
1795803737 22
1795803742 22
1795803747 22
```
</details>

---

