---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-20 12:18:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 421 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 831 |
| Sample Rate | 13.85/sec |
| Health Score | 866% |
| Threads | 9 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1792512717 27
1792512722 27
1792512727 29
1792512732 29
1792512737 29
1792512742 29
1792512747 29
1792512752 29
1792512757 29
1792512762 29
1792512767 29
1792512772 29
1792512777 29
1792512782 29
1792512787 29
1792512792 29
1792512797 29
1792512802 29
1792512807 29
1792512812 29
```
</details>

---

