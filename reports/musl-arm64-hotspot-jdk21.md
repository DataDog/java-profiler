---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-21 11:10:42 EDT

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (5 unique values: 43-48 cores)</summary>

```
1787324705 45
1787324710 45
1787324715 45
1787324720 43
1787324726 43
1787324731 43
1787324736 43
1787324741 43
1787324746 43
1787324751 43
1787324756 43
1787324761 43
1787324766 43
1787324771 46
1787324776 46
1787324781 46
1787324786 46
1787324791 44
1787324796 44
1787324801 44
```
</details>

---

