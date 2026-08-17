---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-17 16:55:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
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
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 12 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1786999821 64
1786999826 64
1786999831 64
1786999836 64
1786999841 64
1786999846 64
1786999851 64
1786999856 64
1786999861 64
1786999866 64
1786999871 64
1786999876 64
1786999881 64
1786999886 64
1786999891 64
1786999896 64
1786999901 64
1786999906 64
1786999911 64
1786999916 64
```
</details>

---

