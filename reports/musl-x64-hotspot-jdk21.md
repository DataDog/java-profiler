---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-11-18 06:08:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 578 |
| Sample Rate | 9.63/sec |
| Health Score | 602% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 0 |
| Sample Rate | 0.00/sec |
| Health Score | 0% |
| Threads | 0 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 74-76 cores)</summary>

```
1794999737 74
1794999742 74
1794999747 74
1794999752 74
1794999757 74
1794999762 74
1794999767 74
1794999772 74
1794999777 76
1794999782 76
1794999787 76
1794999792 76
1794999797 76
1794999802 76
1794999807 76
1794999812 76
1794999817 76
1794999822 76
1794999827 76
1794999832 76
```
</details>

---

