---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 09:26:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 10 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 76 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789737647 48
1789737652 48
1789737657 48
1789737662 48
1789737667 48
1789737672 48
1789737677 48
1789737682 48
1789737687 48
1789737692 48
1789737697 48
1789737702 48
1789737707 48
1789737712 48
1789737717 48
1789737722 43
1789737728 43
1789737733 43
1789737738 43
1789737743 43
```
</details>

---

