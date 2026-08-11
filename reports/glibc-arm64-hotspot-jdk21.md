---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-11 12:25:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 78 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1786465124 34
1786465129 30
1786465134 30
1786465139 30
1786465144 30
1786465149 30
1786465154 30
1786465159 30
1786465164 30
1786465169 30
1786465174 30
1786465179 30
1786465184 30
1786465189 30
1786465194 30
1786465199 34
1786465204 34
1786465209 29
1786465214 29
1786465219 29
```
</details>

---

