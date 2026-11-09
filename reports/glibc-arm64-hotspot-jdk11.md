---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 12:24:35 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 10 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1794244796 48
1794244801 48
1794244806 48
1794244811 48
1794244816 48
1794244821 48
1794244826 48
1794244831 48
1794244836 48
1794244841 48
1794244846 48
1794244851 48
1794244856 48
1794244861 48
1794244866 48
1794244871 48
1794244876 48
1794244881 48
1794244886 48
1794244891 48
```
</details>

---

