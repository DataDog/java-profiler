---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-12 09:20:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 49 |
| Sample Rate | 0.82/sec |
| Health Score | 51% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 10 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 51-59 cores)</summary>

```
1778591612 51
1778591617 51
1778591622 51
1778591627 51
1778591632 51
1778591637 51
1778591642 55
1778591647 55
1778591652 55
1778591657 55
1778591662 55
1778591667 55
1778591672 55
1778591677 55
1778591682 55
1778591687 55
1778591692 55
1778591697 55
1778591702 59
1778591707 59
```
</details>

---

