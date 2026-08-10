---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-10 08:31:27 EDT

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
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 11 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (3 unique values: 22-27 cores)</summary>

```
1786364676 26
1786364681 26
1786364686 26
1786364691 26
1786364696 27
1786364701 27
1786364706 27
1786364711 27
1786364716 27
1786364721 27
1786364726 27
1786364731 27
1786364736 27
1786364741 27
1786364746 27
1786364751 27
1786364756 27
1786364761 27
1786364766 27
1786364771 27
```
</details>

---

