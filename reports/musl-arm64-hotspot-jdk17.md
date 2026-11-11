---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 06:36:23 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 34-46 cores)</summary>

```
1794396698 46
1794396703 46
1794396708 46
1794396713 46
1794396718 46
1794396723 46
1794396728 46
1794396733 46
1794396738 46
1794396743 46
1794396748 46
1794396753 46
1794396758 34
1794396763 34
1794396768 34
1794396773 34
1794396778 39
1794396783 39
1794396788 39
1794396793 39
```
</details>

---

