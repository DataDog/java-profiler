---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 05:46:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1794393737 63
1794393742 63
1794393747 63
1794393752 61
1794393757 61
1794393762 61
1794393767 61
1794393772 61
1794393777 61
1794393782 61
1794393787 61
1794393792 61
1794393797 61
1794393802 61
1794393807 61
1794393812 61
1794393817 61
1794393822 61
1794393827 61
1794393832 61
```
</details>

---

