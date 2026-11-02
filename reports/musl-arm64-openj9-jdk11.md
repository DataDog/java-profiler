---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 07:03:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 15 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
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
1793620845 48
1793620850 48
1793620855 48
1793620860 48
1793620865 48
1793620870 48
1793620875 48
1793620880 48
```
</details>

---

