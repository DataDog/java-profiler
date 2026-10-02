---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-02 05:51:49 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 9 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 11 |
| Allocations | 151 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1790934472 48
1790934477 48
1790934482 48
1790934487 48
1790934492 48
1790934497 48
1790934502 48
1790934507 48
1790934512 48
1790934517 48
1790934522 48
1790934527 40
1790934532 40
1790934537 40
1790934542 40
1790934547 40
1790934552 40
1790934557 40
1790934562 40
1790934567 40
```
</details>

---

