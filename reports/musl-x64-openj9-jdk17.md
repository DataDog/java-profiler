---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-20 12:18:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 636 |
| Sample Rate | 10.60/sec |
| Health Score | 662% |
| Threads | 10 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1792512722 32
1792512727 32
1792512732 32
1792512737 32
1792512742 32
1792512747 32
1792512752 32
1792512757 32
1792512762 32
1792512767 32
1792512772 32
1792512777 32
1792512782 32
1792512787 32
1792512792 32
1792512797 32
1792512802 32
1792512807 32
1792512812 32
1792512817 32
```
</details>

---

