---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-04 18:30:13 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 402 |
| Sample Rate | 6.70/sec |
| Health Score | 419% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1793834750 48
1793834755 48
1793834760 48
1793834765 48
1793834770 48
1793834775 48
1793834781 48
1793834786 48
1793834791 48
1793834796 48
1793834801 46
1793834806 46
1793834811 46
1793834816 46
1793834821 46
1793834826 46
1793834831 46
1793834836 46
1793834841 46
1793834846 48
```
</details>

---

