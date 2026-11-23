---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:05:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795449506 64
1795449511 64
1795449516 64
1795449521 64
1795449526 64
1795449531 64
1795449536 64
1795449541 64
1795449546 64
1795449551 64
1795449556 64
1795449561 64
1795449566 64
1795449571 64
1795449576 64
1795449581 64
1795449586 64
1795449591 64
1795449596 64
1795449601 64
```
</details>

---

