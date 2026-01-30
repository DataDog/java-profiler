---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ❌ FAIL

**Date:** 2026-01-30 06:15:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 32 |
| Sample Rate | 0.53/sec |
| Health Score | 33% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769771571 24
1769771576 24
1769771581 24
1769771586 24
1769771591 24
1769771596 24
1769771601 24
1769771606 24
1769771611 24
1769771616 24
1769771621 24
1769771626 24
1769771631 24
1769771636 24
1769771641 24
1769771646 24
1769771651 24
1769771656 24
1769771661 24
1769771666 24
```
</details>

---

