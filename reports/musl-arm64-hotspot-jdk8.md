---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-17 19:15:40 EDT

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 38-47 cores)</summary>

```
1789686622 47
1789686627 47
1789686632 47
1789686637 47
1789686642 47
1789686647 47
1789686652 47
1789686657 38
1789686662 38
1789686667 38
1789686672 38
1789686677 38
1789686682 38
1789686687 38
1789686692 38
1789686697 38
1789686702 38
1789686707 43
1789686712 43
1789686717 43
```
</details>

---

