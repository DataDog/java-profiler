---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 09:10:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 78-87 cores)</summary>

```
1795010727 78
1795010732 78
1795010737 78
1795010742 78
1795010747 78
1795010752 78
1795010757 78
1795010762 78
1795010767 78
1795010772 78
1795010777 78
1795010782 78
1795010787 87
1795010792 87
1795010797 85
1795010802 85
1795010808 85
1795010813 85
1795010818 85
1795010823 85
```
</details>

---

