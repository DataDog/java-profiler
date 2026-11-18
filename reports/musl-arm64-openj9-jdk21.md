---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:10:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 888 |
| Sample Rate | 14.80/sec |
| Health Score | 925% |
| Threads | 11 |
| Allocations | 527 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1795010717 46
1795010722 46
1795010727 46
1795010732 46
1795010737 46
1795010742 46
1795010747 46
1795010752 46
1795010757 46
1795010762 46
1795010767 46
1795010772 46
1795010777 46
1795010782 46
1795010787 46
1795010792 46
1795010797 46
1795010802 51
1795010807 51
1795010812 51
```
</details>

---

