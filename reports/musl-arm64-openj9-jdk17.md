---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 07:03:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 9 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 9 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793620770 48
1793620775 48
1793620780 48
1793620785 48
1793620790 48
1793620795 48
1793620800 48
1793620805 48
1793620810 48
1793620815 48
1793620820 48
1793620825 48
1793620830 48
1793620835 48
1793620840 48
1793620845 43
1793620850 43
1793620855 43
1793620860 43
1793620865 43
```
</details>

---

