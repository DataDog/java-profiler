---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 00:08:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 42 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 8 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 980 |
| Sample Rate | 16.33/sec |
| Health Score | 1021% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 42-63 cores)</summary>

```
1794459796 42
1794459801 42
1794459806 42
1794459811 42
1794459816 42
1794459821 42
1794459826 42
1794459831 42
1794459836 42
1794459841 42
1794459846 42
1794459851 63
1794459856 63
1794459861 63
1794459866 63
1794459871 61
1794459876 61
1794459881 61
1794459886 61
1794459891 61
```
</details>

---

