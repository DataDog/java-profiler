---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 06:08:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 57-79 cores)</summary>

```
1794999747 79
1794999752 79
1794999757 79
1794999762 79
1794999767 79
1794999772 79
1794999777 79
1794999782 79
1794999787 57
1794999792 57
1794999797 57
1794999802 57
1794999807 57
1794999812 57
1794999817 57
1794999822 57
1794999827 57
1794999832 57
1794999837 57
1794999842 57
```
</details>

---

