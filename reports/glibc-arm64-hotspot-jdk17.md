---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 05:53:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 26 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 9 |
| Allocations | 142 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 315 |
| Sample Rate | 5.25/sec |
| Health Score | 328% |
| Threads | 12 |
| Allocations | 101 |

<details>
<summary>CPU Timeline (2 unique values: 26-30 cores)</summary>

```
1795603758 26
1795603763 26
1795603768 26
1795603773 26
1795603778 26
1795603783 26
1795603788 26
1795603793 26
1795603798 26
1795603803 26
1795603808 30
1795603813 30
1795603818 30
1795603823 30
1795603828 30
1795603833 30
1795603838 30
1795603843 30
1795603848 30
1795603853 30
```
</details>

---

