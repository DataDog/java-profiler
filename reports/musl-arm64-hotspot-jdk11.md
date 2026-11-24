---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:18:53 EST

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 11 |
| Allocations | 174 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 413 |
| Sample Rate | 6.88/sec |
| Health Score | 430% |
| Threads | 14 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795529683 43
1795529688 43
1795529693 43
1795529698 43
1795529703 43
1795529709 43
1795529714 43
1795529719 43
1795529724 48
1795529729 48
1795529734 48
1795529739 43
1795529744 43
1795529749 43
1795529754 43
1795529759 43
1795529764 43
1795529769 43
1795529774 43
1795529779 43
```
</details>

---

