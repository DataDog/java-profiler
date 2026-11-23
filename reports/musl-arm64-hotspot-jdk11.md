---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:39:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795451633 49
1795451638 49
1795451643 49
1795451648 49
1795451653 49
1795451658 49
1795451663 49
1795451668 49
1795451673 49
1795451678 49
1795451683 49
1795451688 49
1795451693 49
1795451698 49
1795451703 49
1795451708 49
1795451713 49
1795451718 49
1795451723 49
1795451728 44
```
</details>

---

