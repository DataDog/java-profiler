---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-09 03:28:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 9 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 12 |
| Allocations | 151 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1791530686 32
1791530691 32
1791530696 32
1791530701 32
1791530706 32
1791530711 32
1791530716 27
1791530721 27
1791530726 27
1791530731 27
1791530736 27
1791530741 27
1791530746 27
1791530751 27
1791530756 27
1791530761 27
1791530766 27
1791530771 27
1791530776 27
1791530781 27
```
</details>

---

