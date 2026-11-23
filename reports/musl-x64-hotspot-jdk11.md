---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 04:42:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 849 |
| Sample Rate | 14.15/sec |
| Health Score | 884% |
| Threads | 12 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 37-59 cores)</summary>

```
1795426659 59
1795426664 59
1795426669 39
1795426674 39
1795426679 39
1795426684 39
1795426689 39
1795426694 39
1795426699 39
1795426704 39
1795426709 39
1795426714 39
1795426719 39
1795426724 39
1795426729 39
1795426734 39
1795426739 39
1795426744 39
1795426749 37
1795426754 37
```
</details>

---

