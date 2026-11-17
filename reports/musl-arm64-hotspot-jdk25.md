---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 10:58:04 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794930687 46
1794930692 46
1794930697 46
1794930702 46
1794930707 46
1794930712 46
1794930717 46
1794930722 46
1794930727 51
1794930732 51
1794930737 51
1794930742 51
1794930747 51
1794930752 51
1794930757 51
1794930763 51
1794930768 51
1794930773 51
1794930778 51
1794930783 51
```
</details>

---

