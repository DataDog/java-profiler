---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-01 12:28:07 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 9 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 264 |
| Sample Rate | 4.40/sec |
| Health Score | 275% |
| Threads | 12 |
| Allocations | 120 |

<details>
<summary>CPU Timeline (2 unique values: 27-32 cores)</summary>

```
1788279663 27
1788279668 27
1788279673 27
1788279678 27
1788279683 27
1788279688 27
1788279693 27
1788279698 27
1788279703 27
1788279708 27
1788279713 27
1788279718 27
1788279723 32
1788279728 32
1788279733 32
1788279738 32
1788279743 32
1788279748 32
1788279753 32
1788279758 32
```
</details>

---

