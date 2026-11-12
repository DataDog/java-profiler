---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-12 00:08:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
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
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1794459776 38
1794459781 38
1794459786 38
1794459791 43
1794459796 43
1794459801 43
1794459806 43
1794459811 43
1794459816 43
1794459821 43
1794459826 43
1794459831 43
1794459836 43
1794459841 43
1794459846 43
1794459851 43
1794459856 43
1794459861 43
1794459866 43
1794459871 43
```
</details>

---

