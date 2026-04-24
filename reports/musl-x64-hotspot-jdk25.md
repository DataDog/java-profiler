---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-24 07:51:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 90 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 418 |
| Sample Rate | 6.97/sec |
| Health Score | 436% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 854 |
| Sample Rate | 14.23/sec |
| Health Score | 889% |
| Threads | 11 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (4 unique values: 85-91 cores)</summary>

```
1777031146 90
1777031151 90
1777031156 90
1777031161 90
1777031166 90
1777031171 90
1777031176 85
1777031181 85
1777031186 85
1777031191 85
1777031196 85
1777031201 85
1777031206 85
1777031211 85
1777031216 85
1777031221 87
1777031226 87
1777031231 87
1777031236 87
1777031241 87
```
</details>

---

