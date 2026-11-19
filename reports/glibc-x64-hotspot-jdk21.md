---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:36:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 633 |
| Sample Rate | 10.55/sec |
| Health Score | 659% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795113149 47
1795113154 47
1795113159 47
1795113164 47
1795113169 47
1795113174 47
1795113179 47
1795113184 47
1795113189 47
1795113194 47
1795113199 47
1795113204 47
1795113209 47
1795113214 47
1795113219 47
1795113224 47
1795113229 47
1795113234 47
1795113239 64
1795113244 64
```
</details>

---

