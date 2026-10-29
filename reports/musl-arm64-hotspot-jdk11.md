---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 09:55:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 14 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1793281776 48
1793281781 48
1793281786 48
1793281791 48
1793281796 48
1793281801 43
1793281806 43
1793281811 43
1793281816 43
1793281821 43
1793281826 43
1793281831 43
1793281836 43
1793281841 43
1793281846 43
1793281851 43
1793281856 43
1793281861 43
1793281866 43
1793281871 43
```
</details>

---

