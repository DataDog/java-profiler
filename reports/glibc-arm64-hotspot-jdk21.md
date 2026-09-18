---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:31:20 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 28 |
| Sample Rate | 0.47/sec |
| Health Score | 29% |
| Threads | 10 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1789737700 47
1789737705 47
1789737710 47
1789737715 47
1789737720 47
1789737725 47
1789737730 42
1789737735 42
1789737740 42
1789737745 42
1789737750 42
1789737755 42
1789737760 42
1789737765 42
1789737770 42
1789737775 42
1789737780 42
1789737785 42
1789737790 42
1789737795 47
```
</details>

---

