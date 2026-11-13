---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 13:06:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 45 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 12 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794592816 32
1794592821 32
1794592826 32
1794592831 32
1794592836 32
1794592841 32
1794592846 32
1794592851 32
1794592856 32
1794592861 32
1794592866 32
1794592871 32
1794592876 32
1794592881 32
1794592886 32
1794592891 32
1794592896 32
1794592901 32
1794592906 32
1794592911 32
```
</details>

---

