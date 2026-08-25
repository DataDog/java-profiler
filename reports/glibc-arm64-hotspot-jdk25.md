---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-25 16:41:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
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
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 11 |
| Allocations | 184 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 66 |
| Sample Rate | 1.10/sec |
| Health Score | 69% |
| Threads | 11 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 24-44 cores)</summary>

```
1787690212 44
1787690217 44
1787690222 44
1787690227 44
1787690232 44
1787690237 44
1787690242 44
1787690247 44
1787690252 44
1787690257 44
1787690262 44
1787690267 44
1787690272 44
1787690277 44
1787690282 44
1787690287 44
1787690292 44
1787690297 24
1787690302 24
1787690307 24
```
</details>

---

