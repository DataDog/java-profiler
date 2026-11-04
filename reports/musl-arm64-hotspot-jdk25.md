---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-04 18:30:13 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 43 |
| Sample Rate | 0.72/sec |
| Health Score | 45% |
| Threads | 8 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (2 unique values: 23-26 cores)</summary>

```
1793834740 26
1793834745 26
1793834750 26
1793834755 26
1793834760 26
1793834765 26
1793834770 26
1793834775 26
1793834780 26
1793834785 26
1793834790 26
1793834795 26
1793834800 26
1793834805 26
1793834810 26
1793834815 26
1793834820 26
1793834825 26
1793834830 23
1793834835 23
```
</details>

---

