---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-22 18:25:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 24-44 cores)</summary>

```
1792707755 44
1792707760 44
1792707765 44
1792707770 44
1792707775 44
1792707780 44
1792707785 44
1792707790 44
1792707795 44
1792707800 44
1792707805 44
1792707810 24
1792707815 24
1792707820 24
1792707825 24
1792707830 24
1792707835 24
1792707840 24
1792707845 24
1792707850 24
```
</details>

---

