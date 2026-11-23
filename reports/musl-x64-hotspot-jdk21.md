---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 04:44:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 55 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 10 |
| Allocations | 450 |

<details>
<summary>CPU Timeline (2 unique values: 53-55 cores)</summary>

```
1795426783 53
1795426788 53
1795426793 53
1795426798 53
1795426803 53
1795426808 53
1795426813 55
1795426818 55
1795426823 55
1795426828 55
1795426833 55
1795426838 55
1795426843 55
1795426848 55
1795426853 55
1795426858 55
1795426863 55
1795426868 55
1795426873 55
1795426878 55
```
</details>

---

