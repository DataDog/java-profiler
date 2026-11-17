---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 14:30:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 11 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (6 unique values: 27-47 cores)</summary>

```
1794943526 32
1794943531 32
1794943536 32
1794943541 32
1794943546 32
1794943551 27
1794943556 27
1794943561 27
1794943566 27
1794943571 27
1794943576 27
1794943581 29
1794943586 29
1794943591 42
1794943596 42
1794943601 47
1794943606 47
1794943611 34
1794943616 34
1794943621 34
```
</details>

---

