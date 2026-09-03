---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-03 05:48:54 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 15 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1788428687 32
1788428692 32
1788428697 32
1788428702 32
1788428707 32
1788428712 32
1788428717 32
1788428722 32
1788428727 32
1788428732 32
1788428737 32
1788428742 32
1788428747 32
1788428752 32
1788428757 32
1788428762 30
1788428767 30
1788428772 30
1788428777 30
1788428782 30
```
</details>

---

